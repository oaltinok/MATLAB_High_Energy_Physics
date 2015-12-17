function createfigure(X1, YMatrix1)
%CREATEFIGURE(X1,YMATRIX1)
%  X1:  vector of x data
%  YMATRIX1:  matrix of y data

%  Auto-generated by MATLAB on 02-Jul-2015 18:05:02

% Create figure
figure1 = figure;

% Create axes
axes1 = axes('Parent',figure1,'PlotBoxAspectRatio',[1 1 1],...
    'FontWeight','bold',...
    'FontSize',16);
%% Uncomment the following line to preserve the X-limits of the axes
% xlim(axes1,[0 2000]);
%% Uncomment the following line to preserve the Y-limits of the axes
% ylim(axes1,[0 2000]);
box(axes1,'on');
hold(axes1,'all');

% Create multiple lines using matrix input to plot
plot1 = plot(X1,YMatrix1,'LineWidth',1,'Parent',axes1);
set(plot1(1),'MarkerFaceColor',[0 0 0],'Marker','.','LineStyle','none',...
    'Color',[0 0 0]);
set(plot1(2),'Color',[0 0 1]);
set(plot1(3),'Color',[0 0.498039215803146 0]);

% Create xlabel
xlabel('Proton Momentum Reconstructed [MeV]','FontWeight','bold',...
    'FontSize',16);

% Create ylabel
ylabel('Proton Momentum True [MeV]','FontWeight','bold','FontSize',16);
